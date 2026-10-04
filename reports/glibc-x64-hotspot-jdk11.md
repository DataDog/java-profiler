---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-04 01:00:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 927 |
| Sample Rate | 15.45/sec |
| Health Score | 966% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 62-76 cores)</summary>

```
1791089717 74
1791089722 74
1791089727 74
1791089732 74
1791089737 76
1791089742 76
1791089747 76
1791089752 76
1791089757 62
1791089762 62
1791089767 62
1791089772 62
1791089777 62
1791089782 62
1791089787 62
1791089792 62
1791089797 62
1791089802 64
1791089807 64
1791089812 64
```
</details>

---


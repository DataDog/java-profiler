---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-04 01:00:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 12 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1791089717 43
1791089722 43
1791089727 43
1791089732 38
1791089737 38
1791089742 38
1791089747 38
1791089752 38
1791089757 38
1791089762 38
1791089767 38
1791089772 38
1791089777 38
1791089782 43
1791089787 43
1791089792 43
1791089797 43
1791089802 43
1791089807 43
1791089812 43
```
</details>

---


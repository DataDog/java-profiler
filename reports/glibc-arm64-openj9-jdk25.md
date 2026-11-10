---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 09:12:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794319717 48
1794319722 48
1794319727 48
1794319732 48
1794319737 48
1794319742 48
1794319747 48
1794319752 48
1794319757 48
1794319762 48
1794319767 48
1794319772 48
1794319777 48
1794319782 48
1794319787 46
1794319792 46
1794319797 46
1794319802 46
1794319807 46
1794319812 46
```
</details>

---


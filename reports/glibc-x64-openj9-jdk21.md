---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:28:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 922 |
| Sample Rate | 15.37/sec |
| Health Score | 961% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1789712687 88
1789712692 88
1789712697 88
1789712702 88
1789712707 88
1789712712 88
1789712717 88
1789712722 88
1789712727 88
1789712732 90
1789712737 90
1789712742 92
1789712747 92
1789712752 92
1789712757 92
1789712762 92
1789712767 92
1789712772 92
1789712777 92
1789712782 92
```
</details>

---


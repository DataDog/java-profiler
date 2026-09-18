---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:32:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (4 unique values: 50-69 cores)</summary>

```
1789712717 69
1789712722 69
1789712727 50
1789712732 50
1789712737 58
1789712742 58
1789712747 58
1789712752 58
1789712757 58
1789712762 58
1789712767 58
1789712772 58
1789712777 58
1789712782 58
1789712787 58
1789712792 58
1789712797 58
1789712802 58
1789712808 58
1789712813 58
```
</details>

---


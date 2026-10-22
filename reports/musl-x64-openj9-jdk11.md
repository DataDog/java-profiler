---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 06:47:01 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 973 |
| Sample Rate | 16.22/sec |
| Health Score | 1014% |
| Threads | 9 |
| Allocations | 563 |

<details>
<summary>CPU Timeline (4 unique values: 54-60 cores)</summary>

```
1792665795 54
1792665800 54
1792665805 56
1792665810 56
1792665815 56
1792665820 56
1792665825 56
1792665830 56
1792665835 56
1792665840 56
1792665845 56
1792665850 56
1792665855 56
1792665860 58
1792665865 58
1792665870 60
1792665875 60
1792665880 60
1792665886 60
1792665891 60
```
</details>

---


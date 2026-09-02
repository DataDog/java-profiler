---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-02 00:58:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1788324828 79
1788324833 79
1788324838 77
1788324843 77
1788324848 77
1788324853 75
1788324858 75
1788324863 75
1788324868 75
1788324873 77
1788324878 77
1788324883 79
1788324888 79
1788324893 79
1788324898 79
1788324903 79
1788324908 79
1788324913 79
1788324918 79
1788324923 79
```
</details>

---


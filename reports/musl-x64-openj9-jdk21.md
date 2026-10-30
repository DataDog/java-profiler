---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 11:47:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 69-79 cores)</summary>

```
1793374851 69
1793374856 71
1793374861 71
1793374866 71
1793374871 71
1793374876 71
1793374881 71
1793374886 71
1793374891 71
1793374896 71
1793374901 79
1793374906 79
1793374911 79
1793374916 79
1793374921 79
1793374926 79
1793374931 79
1793374936 79
1793374941 79
1793374946 79
```
</details>

---


---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 20:50:54 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 963 |
| Sample Rate | 16.05/sec |
| Health Score | 1003% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 80-85 cores)</summary>

```
1778546843 80
1778546848 80
1778546853 80
1778546858 80
1778546863 80
1778546868 80
1778546873 80
1778546878 80
1778546883 80
1778546888 80
1778546893 80
1778546898 80
1778546903 80
1778546908 80
1778546913 85
1778546918 85
1778546923 85
1778546928 85
1778546933 85
1778546938 85
```
</details>

---


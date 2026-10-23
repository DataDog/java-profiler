---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 18:06:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1023 |
| Sample Rate | 17.05/sec |
| Health Score | 1066% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792792892 64
1792792897 64
1792792902 64
1792792907 64
1792792912 64
1792792918 64
1792792923 64
1792792928 64
1792792933 64
1792792938 64
1792792943 64
1792792948 64
1792792953 64
1792792958 64
1792792963 64
1792792968 64
1792792973 64
1792792978 64
1792792983 64
1792792988 64
```
</details>

---


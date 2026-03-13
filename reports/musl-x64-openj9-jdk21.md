---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 07:10:03 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 978 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 12 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 59-79 cores)</summary>

```
1773399898 63
1773399903 63
1773399908 63
1773399913 63
1773399918 63
1773399923 63
1773399928 63
1773399933 63
1773399938 59
1773399943 59
1773399948 59
1773399953 59
1773399958 59
1773399963 59
1773399968 59
1773399973 59
1773399978 59
1773399983 59
1773399988 59
1773399993 59
```
</details>

---


---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 05:51:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787132871 64
1787132876 64
1787132881 64
1787132886 64
1787132891 64
1787132896 64
1787132901 64
1787132906 64
1787132911 64
1787132916 64
1787132921 64
1787132926 64
1787132931 64
1787132936 64
1787132941 64
1787132946 64
1787132951 64
1787132956 64
1787132961 64
1787132966 64
```
</details>

---


---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 10:59:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 10 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1792075944 48
1792075949 48
1792075954 48
1792075959 48
1792075964 48
1792075969 48
1792075974 48
1792075979 48
1792075984 48
1792075989 40
1792075994 40
1792075999 40
1792076004 40
1792076009 40
1792076014 40
1792076019 40
1792076024 40
1792076030 40
1792076035 40
1792076040 40
```
</details>

---


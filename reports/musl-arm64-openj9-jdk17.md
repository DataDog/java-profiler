---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-25 05:49:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1787650985 22
1787650990 17
1787650995 17
1787651000 17
1787651005 17
1787651010 17
1787651015 17
1787651020 17
1787651025 17
1787651030 17
1787651035 17
1787651040 22
1787651045 22
1787651050 22
1787651055 22
1787651060 22
1787651065 22
1787651070 22
1787651075 22
1787651080 22
```
</details>

---


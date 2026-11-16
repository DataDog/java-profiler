---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:38:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 10 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1794832426 45
1794832431 46
1794832436 46
1794832441 48
1794832446 48
1794832451 48
1794832456 48
1794832462 48
1794832467 48
1794832472 48
1794832477 48
1794832482 48
1794832487 48
1794832492 48
1794832497 48
1794832502 48
1794832507 48
1794832512 48
1794832517 48
1794832522 48
```
</details>

---


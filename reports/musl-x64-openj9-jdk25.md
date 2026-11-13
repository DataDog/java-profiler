---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:26:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 50-79 cores)</summary>

```
1794572479 50
1794572484 50
1794572489 50
1794572494 50
1794572499 50
1794572504 50
1794572509 50
1794572514 50
1794572519 50
1794572524 50
1794572529 57
1794572534 57
1794572539 57
1794572544 57
1794572549 57
1794572554 57
1794572559 57
1794572564 57
1794572569 79
1794572574 79
```
</details>

---


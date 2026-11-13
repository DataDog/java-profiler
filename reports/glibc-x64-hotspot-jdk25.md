---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:26:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1794572524 81
1794572529 81
1794572534 78
1794572539 78
1794572544 76
1794572549 76
1794572554 76
1794572559 76
1794572564 76
1794572569 76
1794572574 76
1794572579 76
1794572584 76
1794572589 76
1794572594 76
1794572599 76
1794572604 76
1794572609 76
1794572614 74
1794572619 74
```
</details>

---


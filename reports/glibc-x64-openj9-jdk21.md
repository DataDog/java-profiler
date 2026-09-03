---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788475521 64
1788475526 64
1788475531 64
1788475536 64
1788475541 64
1788475546 64
1788475551 64
1788475556 64
1788475561 64
1788475566 62
1788475571 62
1788475576 62
1788475581 62
1788475586 62
1788475591 62
1788475596 64
1788475601 64
1788475606 64
1788475611 64
1788475616 62
```
</details>

---


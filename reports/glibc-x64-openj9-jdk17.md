---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-25 08:54:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1792932531 61
1792932536 61
1792932541 61
1792932546 61
1792932551 61
1792932556 61
1792932561 63
1792932566 63
1792932571 63
1792932576 63
1792932581 63
1792932586 63
1792932591 63
1792932596 63
1792932601 61
1792932606 61
1792932611 61
1792932616 61
1792932621 61
1792932626 61
```
</details>

---


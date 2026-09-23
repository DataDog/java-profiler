---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 12:10:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790179536 48
1790179541 48
1790179546 48
1790179551 48
1790179556 48
1790179561 48
1790179566 48
1790179571 48
1790179576 48
1790179581 48
1790179586 48
1790179591 48
1790179596 48
1790179602 48
1790179607 48
1790179612 48
1790179617 48
1790179622 48
1790179627 48
1790179632 48
```
</details>

---


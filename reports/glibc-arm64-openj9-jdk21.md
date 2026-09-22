---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 11:27:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 11 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790090516 50
1790090521 50
1790090526 50
1790090531 50
1790090536 50
1790090541 50
1790090546 50
1790090551 50
1790090556 50
1790090561 50
1790090566 50
1790090571 50
1790090576 50
1790090581 50
1790090586 50
1790090591 50
1790090596 50
1790090601 50
1790090606 50
1790090611 50
```
</details>

---


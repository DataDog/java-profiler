---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-24 05:55:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792835521 48
1792835526 48
1792835531 48
1792835536 48
1792835541 48
1792835546 48
1792835551 48
1792835556 48
1792835561 48
1792835566 43
1792835571 43
1792835576 43
1792835581 43
1792835586 43
1792835591 43
1792835596 43
1792835601 43
1792835606 48
1792835611 48
1792835616 48
```
</details>

---


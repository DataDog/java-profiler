---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 81-94 cores)</summary>

```
1792785516 94
1792785521 92
1792785526 92
1792785531 92
1792785536 92
1792785541 92
1792785546 83
1792785551 83
1792785556 83
1792785561 83
1792785566 83
1792785571 83
1792785576 83
1792785581 85
1792785586 85
1792785591 85
1792785596 85
1792785601 85
1792785606 83
1792785611 83
```
</details>

---


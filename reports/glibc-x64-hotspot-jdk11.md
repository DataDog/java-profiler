---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 19:11:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 893 |
| Sample Rate | 14.88/sec |
| Health Score | 930% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 67-71 cores)</summary>

```
1789686381 67
1789686386 67
1789686391 67
1789686396 67
1789686401 67
1789686406 67
1789686411 67
1789686416 67
1789686421 67
1789686426 67
1789686431 67
1789686436 67
1789686441 71
1789686446 71
1789686451 71
1789686456 71
1789686461 71
1789686466 71
1789686471 71
1789686476 71
```
</details>

---


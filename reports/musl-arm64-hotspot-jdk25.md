---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 00:07:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793768532 32
1793768537 32
1793768542 32
1793768547 32
1793768552 32
1793768557 32
1793768562 32
1793768567 32
1793768572 32
1793768577 32
1793768582 32
1793768587 32
1793768592 32
1793768597 32
1793768602 32
1793768607 32
1793768612 32
1793768617 32
1793768622 32
1793768627 32
```
</details>

---


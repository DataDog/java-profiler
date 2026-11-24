---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 12:19:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795540492 64
1795540497 64
1795540502 64
1795540507 64
1795540512 64
1795540517 64
1795540522 64
1795540527 64
1795540532 64
1795540537 64
1795540542 64
1795540547 64
1795540552 64
1795540557 64
1795540562 64
1795540567 64
1795540572 64
1795540577 64
1795540582 64
1795540587 64
```
</details>

---


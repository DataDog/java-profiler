---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 09:55:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1106 |
| Sample Rate | 18.43/sec |
| Health Score | 1152% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787147521 64
1787147526 64
1787147531 64
1787147536 64
1787147541 64
1787147546 64
1787147551 64
1787147556 64
1787147561 64
1787147566 64
1787147571 64
1787147576 64
1787147581 64
1787147586 64
1787147591 64
1787147596 64
1787147601 64
1787147606 64
1787147611 64
1787147616 64
```
</details>

---


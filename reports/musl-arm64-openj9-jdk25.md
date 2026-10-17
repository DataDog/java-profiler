---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-17 05:53:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792230521 32
1792230526 32
1792230531 32
1792230536 32
1792230541 32
1792230546 32
1792230551 32
1792230556 32
1792230561 32
1792230566 32
1792230571 32
1792230576 32
1792230581 32
1792230586 32
1792230591 32
1792230596 32
1792230601 32
1792230606 32
1792230611 32
1792230616 32
```
</details>

---


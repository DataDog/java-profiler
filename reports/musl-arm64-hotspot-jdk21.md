---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 11:51:14 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 15 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1795538743 56
1795538748 56
1795538753 56
1795538758 56
1795538763 56
1795538768 56
1795538773 56
1795538778 56
1795538783 56
1795538788 56
1795538793 56
1795538798 56
1795538803 56
1795538808 56
1795538813 56
1795538818 56
1795538823 64
1795538828 64
1795538833 64
1795538838 64
```
</details>

---


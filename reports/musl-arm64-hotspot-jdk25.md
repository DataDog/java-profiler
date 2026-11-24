---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:51:14 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 41-52 cores)</summary>

```
1795538748 41
1795538753 41
1795538758 41
1795538763 41
1795538768 41
1795538773 41
1795538778 41
1795538783 41
1795538788 41
1795538793 41
1795538798 41
1795538803 47
1795538808 47
1795538813 47
1795538818 47
1795538823 47
1795538828 47
1795538833 47
1795538838 47
1795538843 47
```
</details>

---


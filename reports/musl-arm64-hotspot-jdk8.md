---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:40:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 35-49 cores)</summary>

```
1789997733 35
1789997738 35
1789997743 35
1789997748 35
1789997753 35
1789997758 35
1789997763 35
1789997768 35
1789997773 35
1789997778 35
1789997783 35
1789997788 35
1789997793 40
1789997798 40
1789997803 40
1789997808 40
1789997813 49
1789997818 49
1789997823 49
1789997828 49
```
</details>

---


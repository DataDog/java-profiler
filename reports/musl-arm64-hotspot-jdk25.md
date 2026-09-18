---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:27:49 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789737651 42
1789737656 42
1789737661 47
1789737666 47
1789737671 47
1789737676 47
1789737681 47
1789737686 47
1789737691 47
1789737696 47
1789737701 47
1789737706 47
1789737711 47
1789737716 47
1789737721 47
1789737726 47
1789737731 42
1789737736 42
1789737741 42
1789737747 42
```
</details>

---


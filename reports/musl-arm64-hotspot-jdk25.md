---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 06:42:06 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795174648 50
1795174653 50
1795174658 50
1795174663 50
1795174668 50
1795174673 50
1795174678 50
1795174683 50
1795174688 50
1795174693 50
1795174698 50
1795174703 50
1795174708 50
1795174713 50
1795174718 50
1795174723 50
1795174728 50
1795174733 50
1795174738 50
1795174743 50
```
</details>

---


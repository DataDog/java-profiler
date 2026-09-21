---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 17:43:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790026698 32
1790026703 32
1790026708 32
1790026713 32
1790026718 32
1790026723 32
1790026728 32
1790026733 32
1790026738 32
1790026743 22
1790026748 22
1790026753 22
1790026758 22
1790026763 22
1790026768 22
1790026773 22
1790026778 22
1790026783 22
1790026788 22
1790026793 22
```
</details>

---


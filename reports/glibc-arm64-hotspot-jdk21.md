---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:54:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 9 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786974688 48
1786974693 48
1786974698 48
1786974703 48
1786974708 48
1786974713 48
1786974718 48
1786974723 48
1786974728 48
1786974733 48
1786974738 48
1786974743 48
1786974748 48
1786974753 43
1786974758 43
1786974763 43
1786974768 43
1786974773 43
1786974778 43
1786974783 43
```
</details>

---


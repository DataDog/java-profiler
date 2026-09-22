---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:52:09 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 43 |
| Sample Rate | 0.72/sec |
| Health Score | 45% |
| Threads | 10 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1790091763 44
1790091768 44
1790091773 44
1790091778 44
1790091783 44
1790091788 48
1790091793 48
1790091798 48
1790091803 48
1790091808 48
1790091813 48
1790091818 48
1790091823 48
1790091828 48
1790091833 48
1790091838 48
1790091843 48
1790091848 48
1790091853 48
1790091858 48
```
</details>

---


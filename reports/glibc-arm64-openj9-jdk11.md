---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:56:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795434737 48
1795434742 48
1795434747 48
1795434752 48
1795434757 48
1795434762 48
1795434767 48
1795434772 48
1795434777 48
1795434782 48
1795434787 48
1795434792 48
1795434797 48
1795434802 48
1795434807 48
1795434812 48
1795434817 48
1795434822 48
1795434827 48
1795434832 64
```
</details>

---


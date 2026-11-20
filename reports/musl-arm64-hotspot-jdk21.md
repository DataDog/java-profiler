---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:56:27 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795171813 50
1795171818 50
1795171823 50
1795171828 50
1795171833 50
1795171838 50
1795171843 50
1795171848 50
1795171853 50
1795171858 50
1795171863 50
1795171868 50
1795171873 50
1795171878 50
1795171883 50
1795171888 50
1795171893 50
1795171898 50
1795171903 50
1795171908 50
```
</details>

---


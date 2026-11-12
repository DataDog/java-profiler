---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:33:54 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 8 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 19-24 cores)</summary>

```
1794508063 19
1794508068 19
1794508073 19
1794508078 21
1794508083 21
1794508088 19
1794508093 19
1794508098 19
1794508103 19
1794508108 19
1794508113 19
1794508118 19
1794508123 19
1794508128 24
1794508133 24
1794508138 24
1794508143 24
1794508148 24
1794508153 24
1794508158 24
```
</details>

---


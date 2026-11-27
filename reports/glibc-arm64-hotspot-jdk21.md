---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 17:07:28 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795817047 64
1795817052 64
1795817057 64
1795817062 64
1795817067 64
1795817072 64
1795817077 64
1795817082 64
1795817087 64
1795817092 64
1795817097 64
1795817102 64
1795817107 64
1795817112 59
1795817117 59
1795817122 59
1795817127 59
1795817132 59
1795817137 59
1795817142 59
```
</details>

---


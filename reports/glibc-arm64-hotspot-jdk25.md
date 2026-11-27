---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 17:07:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795817067 64
1795817072 64
1795817077 64
1795817082 64
1795817087 64
1795817092 64
1795817097 64
1795817102 64
1795817107 64
1795817112 64
1795817117 59
1795817122 59
1795817127 59
1795817132 59
1795817137 59
1795817142 59
1795817147 59
1795817152 59
1795817157 59
1795817162 59
```
</details>

---


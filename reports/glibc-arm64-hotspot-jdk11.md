---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 21:04:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 34-40 cores)</summary>

```
1794707983 34
1794707988 34
1794707993 34
1794707998 40
1794708003 40
1794708008 40
1794708013 40
1794708018 40
1794708023 40
1794708028 40
1794708033 40
1794708038 40
1794708043 40
1794708048 40
1794708054 40
1794708059 40
1794708064 40
1794708069 40
1794708074 40
1794708079 40
```
</details>

---


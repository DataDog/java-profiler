---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:47:32 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 996 |
| Sample Rate | 16.60/sec |
| Health Score | 1038% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1795200171 31
1795200176 31
1795200181 36
1795200186 36
1795200191 36
1795200196 36
1795200201 36
1795200206 36
1795200211 36
1795200216 36
1795200221 36
1795200226 36
1795200231 36
1795200236 31
1795200241 31
1795200246 31
1795200251 31
1795200256 31
1795200261 31
1795200266 31
```
</details>

---


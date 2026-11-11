---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:07:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 91-94 cores)</summary>

```
1794394963 91
1794394968 91
1794394973 91
1794394978 91
1794394983 91
1794394988 91
1794394993 91
1794394998 91
1794395003 91
1794395008 91
1794395013 91
1794395018 94
1794395023 94
1794395028 94
1794395033 94
1794395038 94
1794395043 94
1794395048 94
1794395053 94
1794395058 94
```
</details>

---


---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:53:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 12 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 18-32 cores)</summary>

```
1770130072 18
1770130077 18
1770130082 18
1770130087 18
1770130092 18
1770130097 18
1770130102 18
1770130107 18
1770130112 28
1770130117 28
1770130122 28
1770130127 28
1770130132 28
1770130137 28
1770130142 28
1770130147 28
1770130152 32
1770130157 32
1770130162 32
1770130167 30
```
</details>

---


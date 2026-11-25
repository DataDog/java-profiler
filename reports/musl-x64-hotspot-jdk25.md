---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 52-69 cores)</summary>

```
1795641190 52
1795641195 52
1795641200 52
1795641205 52
1795641210 52
1795641215 52
1795641220 69
1795641225 69
1795641230 69
1795641235 69
1795641240 69
1795641245 69
1795641250 69
1795641255 69
1795641260 69
1795641265 69
1795641270 69
1795641275 69
1795641280 69
1795641285 69
```
</details>

---


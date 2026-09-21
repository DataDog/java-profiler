---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789992197 48
1789992202 48
1789992207 48
1789992212 43
1789992217 43
1789992222 43
1789992227 43
1789992232 43
1789992237 43
1789992242 43
1789992247 43
1789992253 43
1789992258 43
1789992263 48
1789992268 48
1789992273 48
1789992278 48
1789992283 48
1789992288 48
1789992293 48
```
</details>

---


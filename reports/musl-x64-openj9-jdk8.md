---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 08:08:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 8-10 cores)</summary>

```
1789992183 8
1789992188 8
1789992193 8
1789992198 10
1789992203 10
1789992208 10
1789992213 10
1789992218 10
1789992223 10
1789992228 10
1789992233 10
1789992238 10
1789992243 10
1789992248 10
1789992253 10
1789992258 10
1789992263 10
1789992268 10
1789992273 10
1789992278 10
```
</details>

---


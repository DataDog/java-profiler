---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:35:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1147 |
| Sample Rate | 19.12/sec |
| Health Score | 1195% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1790332176 92
1790332181 92
1790332186 92
1790332191 92
1790332196 92
1790332201 92
1790332206 92
1790332211 92
1790332216 92
1790332221 92
1790332226 92
1790332231 92
1790332236 92
1790332241 96
1790332246 96
1790332251 96
1790332256 96
1790332261 96
1790332266 96
1790332271 96
```
</details>

---


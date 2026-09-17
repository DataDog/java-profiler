---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 18:05:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 15 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789682086 43
1789682091 48
1789682096 48
1789682101 48
1789682106 48
1789682111 48
1789682116 48
1789682121 45
1789682126 45
1789682131 45
1789682136 45
1789682141 45
1789682146 45
1789682151 45
1789682156 45
1789682161 45
1789682166 45
1789682172 45
1789682177 45
1789682182 45
```
</details>

---


---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:53:47 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792144079 48
1792144084 48
1792144089 48
1792144094 48
1792144099 48
1792144104 43
1792144109 43
1792144114 43
1792144119 43
1792144124 43
1792144129 43
1792144134 43
1792144139 43
1792144144 43
1792144150 43
1792144155 43
1792144160 43
1792144165 43
1792144170 43
1792144175 48
```
</details>

---


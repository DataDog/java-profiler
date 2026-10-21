---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 17:49:35 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 33-44 cores)</summary>

```
1792619113 44
1792619118 44
1792619123 44
1792619128 44
1792619133 44
1792619138 44
1792619143 44
1792619148 44
1792619153 44
1792619158 44
1792619163 44
1792619168 44
1792619173 44
1792619178 44
1792619183 33
1792619188 33
1792619193 33
1792619198 33
1792619203 33
1792619208 33
```
</details>

---


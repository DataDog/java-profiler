---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 00:07:36 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 14 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1794546159 19
1794546164 19
1794546169 19
1794546174 19
1794546179 19
1794546184 19
1794546189 19
1794546194 19
1794546199 19
1794546204 19
1794546209 19
1794546214 19
1794546219 19
1794546224 24
1794546229 24
1794546234 24
1794546239 24
1794546244 24
1794546249 24
1794546254 24
```
</details>

---


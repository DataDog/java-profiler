---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 00:07:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1794546139 33
1794546144 33
1794546149 33
1794546154 33
1794546159 33
1794546164 35
1794546169 35
1794546174 35
1794546179 35
1794546184 40
1794546189 40
1794546194 40
1794546199 40
1794546204 40
1794546209 40
1794546214 40
1794546219 40
1794546224 40
1794546229 40
1794546234 40
```
</details>

---


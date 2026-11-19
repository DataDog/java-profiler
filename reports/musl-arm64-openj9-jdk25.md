---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:36:50 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 13 |
| Allocations | 192 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795113146 45
1795113151 45
1795113156 45
1795113161 45
1795113166 45
1795113171 45
1795113176 45
1795113181 45
1795113186 45
1795113191 45
1795113196 45
1795113201 45
1795113206 50
1795113211 50
1795113216 50
1795113221 50
1795113226 50
1795113231 50
1795113236 50
1795113241 50
```
</details>

---


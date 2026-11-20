---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 11:32:48 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 15-64 cores)</summary>

```
1795192116 29
1795192121 29
1795192126 29
1795192131 29
1795192136 29
1795192141 29
1795192146 29
1795192151 29
1795192156 64
1795192161 64
1795192166 29
1795192171 29
1795192176 29
1795192181 29
1795192186 29
1795192191 29
1795192196 29
1795192201 29
1795192206 29
1795192211 29
```
</details>

---


---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 15:18:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 31-43 cores)</summary>

```
1792610085 43
1792610090 43
1792610095 43
1792610100 43
1792610105 43
1792610110 36
1792610115 36
1792610120 36
1792610125 36
1792610130 36
1792610135 36
1792610140 36
1792610145 36
1792610150 36
1792610155 36
1792610160 36
1792610165 36
1792610170 31
1792610175 31
1792610180 31
```
</details>

---


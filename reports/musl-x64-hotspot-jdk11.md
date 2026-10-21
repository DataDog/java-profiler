---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 15:18:46 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 10 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (4 unique values: 55-63 cores)</summary>

```
1792610090 61
1792610095 61
1792610100 61
1792610105 61
1792610110 61
1792610115 61
1792610120 61
1792610125 61
1792610130 63
1792610135 63
1792610140 63
1792610145 63
1792610150 63
1792610155 63
1792610160 63
1792610165 63
1792610170 55
1792610175 55
1792610180 57
1792610185 57
```
</details>

---


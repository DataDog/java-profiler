---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 41-88 cores)</summary>

```
1790084788 88
1790084793 88
1790084798 63
1790084803 63
1790084808 63
1790084813 63
1790084818 63
1790084823 63
1790084828 63
1790084833 63
1790084838 63
1790084843 63
1790084848 63
1790084853 63
1790084858 63
1790084863 63
1790084868 41
1790084873 41
1790084878 41
1790084883 41
```
</details>

---

